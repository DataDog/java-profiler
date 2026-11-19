---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:30:02 EST

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 11 |
| Allocations | 167 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1795112663 9
1795112668 9
1795112673 9
1795112678 9
1795112683 9
1795112688 9
1795112693 9
1795112698 9
1795112703 9
1795112708 29
1795112713 29
1795112718 29
1795112723 29
1795112728 29
1795112733 29
1795112738 29
1795112743 29
1795112748 29
1795112753 29
1795112758 29
```
</details>

---

