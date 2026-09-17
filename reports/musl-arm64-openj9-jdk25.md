---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 16:51:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 16 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789677900 43
1789677905 48
1789677910 48
1789677915 48
1789677920 45
1789677925 45
1789677930 45
1789677935 45
1789677940 45
1789677945 45
1789677950 45
1789677955 45
1789677960 45
1789677965 45
1789677970 45
1789677976 45
1789677981 45
1789677986 45
1789677991 45
1789677996 45
```
</details>

---

