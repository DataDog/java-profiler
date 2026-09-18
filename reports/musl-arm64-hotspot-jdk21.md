---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1789737736 36
1789737741 36
1789737746 36
1789737751 36
1789737756 36
1789737762 36
1789737767 36
1789737772 36
1789737777 36
1789737782 36
1789737787 48
1789737792 48
1789737797 48
1789737802 48
1789737807 48
1789737812 48
1789737817 48
1789737822 36
1789737827 36
1789737832 36
```
</details>

---

