---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 07:12:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 96 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 11 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1791544014 39
1791544019 51
1791544024 51
1791544029 51
1791544034 51
1791544039 51
1791544044 51
1791544049 51
1791544054 51
1791544059 51
1791544064 51
1791544069 51
1791544074 51
1791544079 51
1791544084 51
1791544089 51
1791544094 51
1791544099 51
1791544104 51
1791544109 51
```
</details>

---

