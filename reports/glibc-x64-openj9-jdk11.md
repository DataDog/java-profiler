---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 09:53:13 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (5 unique values: 26-42 cores)</summary>

```
1770130096 26
1770130101 26
1770130106 26
1770130111 26
1770130116 26
1770130121 26
1770130126 26
1770130131 26
1770130136 28
1770130141 28
1770130146 42
1770130151 42
1770130156 30
1770130161 30
1770130166 30
1770130171 32
1770130176 32
1770130181 32
1770130186 32
1770130191 32
```
</details>

---

