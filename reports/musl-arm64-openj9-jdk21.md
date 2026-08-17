---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:06:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 7 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 10 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (6 unique values: 38-48 cores)</summary>

```
1786971596 48
1786971601 48
1786971606 38
1786971611 38
1786971616 38
1786971621 38
1786971626 38
1786971631 38
1786971636 38
1786971641 38
1786971646 43
1786971651 43
1786971656 43
1786971661 42
1786971666 42
1786971671 47
1786971676 47
1786971681 47
1786971686 47
1786971691 48
```
</details>

---

