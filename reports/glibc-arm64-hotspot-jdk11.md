---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:53:45 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 14 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789677835 38
1789677840 43
1789677845 43
1789677850 48
1789677855 48
1789677860 48
1789677865 48
1789677870 48
1789677875 48
1789677880 48
1789677885 48
1789677890 48
1789677895 48
1789677900 48
1789677905 48
1789677910 48
1789677915 48
1789677920 48
1789677925 48
1789677930 48
```
</details>

---

