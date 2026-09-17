---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 16:56:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 84-94 cores)</summary>

```
1789678017 94
1789678022 94
1789678027 93
1789678032 93
1789678037 93
1789678042 93
1789678047 93
1789678052 93
1789678057 93
1789678062 91
1789678067 91
1789678072 91
1789678077 91
1789678082 92
1789678087 92
1789678092 92
1789678097 92
1789678102 92
1789678107 92
1789678112 92
```
</details>

---

