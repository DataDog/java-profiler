---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-10 05:51:03 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791625634 32
1791625639 32
1791625644 32
1791625649 32
1791625654 32
1791625659 32
1791625664 32
1791625669 32
1791625674 32
1791625679 32
1791625684 32
1791625689 32
1791625694 32
1791625699 32
1791625704 32
1791625709 32
1791625714 32
1791625719 32
1791625724 32
1791625729 32
```
</details>

---

