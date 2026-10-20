---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 10:08:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 15 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1792505014 49
1792505019 49
1792505024 49
1792505029 49
1792505034 44
1792505039 44
1792505044 44
1792505049 44
1792505054 44
1792505059 44
1792505064 44
1792505069 44
1792505074 44
1792505079 44
1792505084 44
1792505089 44
1792505094 44
1792505099 44
1792505104 44
1792505109 44
```
</details>

---

