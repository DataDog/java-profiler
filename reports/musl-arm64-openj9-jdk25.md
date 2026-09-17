---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:42:10 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 12 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789673555 46
1789673560 46
1789673566 46
1789673571 46
1789673576 46
1789673581 46
1789673586 46
1789673591 46
1789673596 46
1789673601 46
1789673606 48
1789673611 48
1789673616 48
1789673621 48
1789673626 48
1789673631 48
1789673636 48
1789673641 48
1789673646 48
1789673651 48
```
</details>

---

