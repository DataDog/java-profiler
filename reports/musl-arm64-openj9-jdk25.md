---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:57:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 9 |
| Allocations | 178 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1789966344 24
1789966349 24
1789966354 24
1789966359 24
1789966364 24
1789966369 24
1789966374 24
1789966379 24
1789966384 24
1789966389 24
1789966394 24
1789966399 24
1789966404 24
1789966409 24
1789966414 29
1789966419 29
1789966424 26
1789966429 26
1789966434 26
1789966439 26
```
</details>

---

