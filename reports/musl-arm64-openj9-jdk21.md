---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-17 05:23:19 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (1 unique values: 38-38 cores)</summary>

```
1794910609 38
1794910614 38
1794910619 38
1794910624 38
1794910629 38
1794910634 38
1794910639 38
1794910644 38
1794910649 38
1794910654 38
1794910659 38
1794910664 38
1794910669 38
1794910674 38
1794910679 38
1794910684 38
1794910689 38
1794910694 38
1794910699 38
1794910704 38
```
</details>

---

