---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:53:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 12 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 35-64 cores)</summary>

```
1770130081 37
1770130086 35
1770130091 35
1770130096 42
1770130101 42
1770130106 42
1770130111 42
1770130116 47
1770130121 47
1770130126 47
1770130131 47
1770130136 47
1770130141 47
1770130146 47
1770130151 47
1770130156 47
1770130161 47
1770130166 47
1770130171 47
1770130176 47
```
</details>

---

