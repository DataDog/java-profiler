---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:29:53 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1789719963 24
1789719968 29
1789719973 29
1789719978 24
1789719983 24
1789719988 29
1789719993 29
1789719998 24
1789720003 24
1789720008 24
1789720013 24
1789720018 29
1789720023 29
1789720028 29
1789720033 29
1789720038 29
1789720043 29
1789720048 29
1789720053 29
1789720058 29
```
</details>

---

