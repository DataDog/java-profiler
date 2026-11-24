---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:39:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 11 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 14 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 39-55 cores)</summary>

```
1795537844 39
1795537849 39
1795537854 39
1795537859 39
1795537865 39
1795537870 39
1795537875 39
1795537880 39
1795537885 39
1795537890 39
1795537895 39
1795537900 39
1795537905 39
1795537910 39
1795537915 39
1795537920 39
1795537925 39
1795537930 55
1795537935 55
1795537940 55
```
</details>

---

