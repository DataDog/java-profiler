---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:52:01 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (5 unique values: 37-48 cores)</summary>

```
1789731979 38
1789731984 38
1789731989 37
1789731994 37
1789731999 37
1789732004 37
1789732009 37
1789732014 37
1789732019 37
1789732024 37
1789732029 37
1789732034 47
1789732039 47
1789732044 47
1789732049 43
1789732054 43
1789732059 43
1789732064 43
1789732069 43
1789732074 43
```
</details>

---

