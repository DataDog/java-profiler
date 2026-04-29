---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 06:49:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1038 |
| Sample Rate | 17.30/sec |
| Health Score | 1081% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777459447 64
1777459452 64
1777459457 64
1777459462 64
1777459467 64
1777459472 64
1777459477 64
1777459482 64
1777459487 64
1777459492 64
1777459497 64
1777459502 64
1777459507 64
1777459512 64
1777459517 64
1777459522 64
1777459527 64
1777459532 64
1777459537 64
1777459542 64
```
</details>

---

