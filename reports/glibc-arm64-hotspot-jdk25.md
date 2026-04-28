---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 07:41:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1777376218 44
1777376223 39
1777376228 39
1777376233 39
1777376238 39
1777376243 39
1777376248 39
1777376253 44
1777376258 44
1777376263 44
1777376268 44
1777376273 44
1777376278 44
1777376283 44
1777376288 44
1777376293 39
1777376298 39
1777376303 39
1777376308 39
1777376313 44
```
</details>

---

