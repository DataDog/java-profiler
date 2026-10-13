---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-13 13:24:01 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 63-96 cores)</summary>

```
1791911875 96
1791911880 96
1791911885 96
1791911890 96
1791911895 96
1791911900 96
1791911905 96
1791911910 96
1791911915 96
1791911920 96
1791911925 96
1791911930 96
1791911935 96
1791911940 63
1791911945 63
1791911950 63
1791911955 63
1791911960 63
1791911965 63
1791911970 63
```
</details>

---

