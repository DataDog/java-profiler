---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 07:41:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (6 unique values: 45-53 cores)</summary>

```
1777376171 51
1777376176 51
1777376181 51
1777376186 49
1777376191 49
1777376196 51
1777376201 51
1777376206 53
1777376211 53
1777376216 53
1777376221 53
1777376226 48
1777376231 48
1777376236 50
1777376241 50
1777376246 50
1777376251 50
1777376256 50
1777376261 50
1777376266 50
```
</details>

---

