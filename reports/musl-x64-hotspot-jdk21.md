---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 12:28:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1792772651 96
1792772656 96
1792772661 96
1792772666 96
1792772671 96
1792772676 96
1792772681 96
1792772686 96
1792772691 96
1792772696 76
1792772701 76
1792772706 76
1792772711 76
1792772716 76
1792772721 76
1792772726 76
1792772731 76
1792772736 76
1792772741 76
1792772746 76
```
</details>

---

