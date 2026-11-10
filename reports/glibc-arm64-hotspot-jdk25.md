---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:09:19 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1794337543 64
1794337548 64
1794337553 64
1794337558 64
1794337563 64
1794337568 64
1794337573 28
1794337578 28
1794337583 28
1794337588 28
1794337593 28
1794337598 28
1794337603 28
1794337608 28
1794337613 28
1794337618 28
1794337623 28
1794337628 28
1794337633 28
1794337638 28
```
</details>

---

