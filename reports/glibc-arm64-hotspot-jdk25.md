---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 14:55:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1788547871 46
1788547876 46
1788547881 46
1788547886 48
1788547891 48
1788547896 48
1788547901 48
1788547906 48
1788547911 48
1788547916 48
1788547921 48
1788547926 48
1788547931 48
1788547936 48
1788547941 48
1788547946 48
1788547951 48
1788547956 48
1788547961 48
1788547966 48
```
</details>

---

