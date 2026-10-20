---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 06:42:10 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 72-92 cores)</summary>

```
1792492584 92
1792492589 92
1792492594 92
1792492600 92
1792492605 92
1792492610 92
1792492615 92
1792492620 92
1792492625 92
1792492630 92
1792492635 92
1792492640 92
1792492645 72
1792492650 72
1792492655 72
1792492660 72
1792492665 72
1792492670 72
1792492675 72
1792492680 72
```
</details>

---

