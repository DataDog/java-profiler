---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 08:18:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 8 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 84-96 cores)</summary>

```
1778069636 96
1778069641 96
1778069646 96
1778069651 96
1778069656 96
1778069661 96
1778069666 96
1778069671 96
1778069676 96
1778069681 84
1778069686 84
1778069691 84
1778069696 84
1778069701 84
1778069706 84
1778069711 84
1778069716 84
1778069721 84
1778069726 84
1778069731 84
```
</details>

---

