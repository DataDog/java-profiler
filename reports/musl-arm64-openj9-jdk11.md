---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:33:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 37-64 cores)</summary>

```
1795631250 47
1795631255 47
1795631260 47
1795631265 47
1795631270 47
1795631275 47
1795631280 37
1795631285 37
1795631290 37
1795631295 37
1795631300 37
1795631305 37
1795631310 37
1795631315 37
1795631320 37
1795631325 37
1795631330 37
1795631335 37
1795631340 37
1795631345 47
```
</details>

---

