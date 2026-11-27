---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:26:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795785643 64
1795785648 64
1795785653 64
1795785658 64
1795785663 64
1795785668 64
1795785673 64
1795785678 64
1795785683 64
1795785688 64
1795785693 64
1795785698 64
1795785703 64
1795785708 64
1795785713 64
1795785718 64
1795785723 64
1795785728 64
1795785733 64
1795785738 64
```
</details>

---

