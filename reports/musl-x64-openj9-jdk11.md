---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 07:41:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 21-26 cores)</summary>

```
1777376164 24
1777376169 24
1777376174 24
1777376179 24
1777376184 24
1777376189 24
1777376194 26
1777376199 26
1777376204 26
1777376209 26
1777376214 22
1777376219 22
1777376224 22
1777376229 22
1777376234 22
1777376239 22
1777376244 25
1777376249 25
1777376254 21
1777376259 21
```
</details>

---

