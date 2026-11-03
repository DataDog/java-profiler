---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 16:51:00 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1793742177 48
1793742182 48
1793742187 48
1793742192 48
1793742197 48
1793742202 48
1793742207 48
1793742212 48
1793742217 48
1793742222 48
1793742227 48
1793742232 48
1793742237 48
1793742242 47
1793742247 47
1793742252 47
1793742257 47
1793742262 47
1793742267 47
1793742272 47
```
</details>

---

