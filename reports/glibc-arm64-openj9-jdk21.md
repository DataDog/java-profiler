---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 04:34:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 27-64 cores)</summary>

```
1789719943 27
1789719948 27
1789719953 27
1789719958 27
1789719963 27
1789719968 47
1789719973 47
1789719978 47
1789719983 47
1789719988 64
1789719993 64
1789719998 64
1789720003 64
1789720008 64
1789720013 64
1789720018 64
1789720023 64
1789720028 64
1789720033 64
1789720038 64
```
</details>

---

