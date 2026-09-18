---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:52:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 10 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (5 unique values: 37-48 cores)</summary>

```
1789731974 38
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
1789732044 43
1789732049 43
1789732054 43
1789732059 43
1789732064 43
1789732069 43
```
</details>

---

