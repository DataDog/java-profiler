---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-08 10:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 61-66 cores)</summary>

```
1791470856 66
1791470861 66
1791470866 66
1791470871 64
1791470876 64
1791470881 64
1791470886 64
1791470891 66
1791470896 66
1791470901 66
1791470906 66
1791470911 66
1791470916 66
1791470921 66
1791470926 66
1791470931 66
1791470936 66
1791470941 66
1791470946 66
1791470951 61
```
</details>

---

