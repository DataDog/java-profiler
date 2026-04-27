---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 16:29:15 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1777321167 59
1777321172 59
1777321177 59
1777321182 59
1777321187 59
1777321192 54
1777321197 54
1777321202 54
1777321207 54
1777321212 54
1777321217 54
1777321222 54
1777321227 54
1777321232 54
1777321237 54
1777321242 54
1777321247 54
1777321252 54
1777321257 54
1777321262 54
```
</details>

---

