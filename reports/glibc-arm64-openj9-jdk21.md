---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 11:55:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1788364293 32
1788364298 32
1788364303 32
1788364308 32
1788364313 32
1788364318 32
1788364323 32
1788364328 32
1788364333 32
1788364338 32
1788364344 32
1788364349 32
1788364354 32
1788364359 32
1788364364 32
1788364369 32
1788364374 32
1788364379 32
1788364384 32
1788364389 32
```
</details>

---

