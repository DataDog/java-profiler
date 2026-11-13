---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:28:32 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794572469 40
1794572474 40
1794572479 40
1794572484 40
1794572489 40
1794572494 40
1794572499 40
1794572504 40
1794572509 40
1794572514 40
1794572519 40
1794572524 40
1794572529 40
1794572534 40
1794572539 40
1794572544 40
1794572549 40
1794572554 40
1794572559 40
1794572564 40
```
</details>

---

