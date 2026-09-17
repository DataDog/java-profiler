---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:56:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 88-91 cores)</summary>

```
1789677886 88
1789677891 88
1789677896 88
1789677901 88
1789677906 88
1789677911 89
1789677916 89
1789677921 89
1789677926 89
1789677931 89
1789677936 89
1789677941 89
1789677946 89
1789677951 89
1789677956 89
1789677961 89
1789677966 89
1789677971 89
1789677976 91
1789677981 91
```
</details>

---

