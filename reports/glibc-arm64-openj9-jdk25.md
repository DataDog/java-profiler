---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 02:28:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1789712695 24
1789712700 24
1789712705 24
1789712710 24
1789712715 29
1789712720 29
1789712725 29
1789712730 29
1789712735 29
1789712740 29
1789712745 29
1789712750 29
1789712755 29
1789712760 29
1789712765 24
1789712770 24
1789712775 24
1789712780 19
1789712785 19
1789712790 19
```
</details>

---

