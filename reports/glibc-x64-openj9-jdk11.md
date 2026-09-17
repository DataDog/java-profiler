---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:30:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 965 |
| Sample Rate | 16.08/sec |
| Health Score | 1005% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1789680144 61
1789680149 61
1789680154 59
1789680159 59
1789680164 61
1789680169 61
1789680174 61
1789680179 61
1789680184 61
1789680189 63
1789680194 63
1789680199 63
1789680204 63
1789680209 63
1789680214 63
1789680219 63
1789680224 63
1789680229 63
1789680234 63
1789680239 63
```
</details>

---

