---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 09:46:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 44-47 cores)</summary>

```
1794580895 47
1794580900 47
1794580905 47
1794580910 47
1794580915 47
1794580920 47
1794580926 47
1794580931 47
1794580936 47
1794580941 47
1794580946 47
1794580951 47
1794580956 47
1794580961 47
1794580966 47
1794580971 47
1794580976 47
1794580981 44
1794580986 44
1794580991 44
```
</details>

---

