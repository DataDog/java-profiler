---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:41:32 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 49 |
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
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 13 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1795199756 64
1795199761 64
1795199766 49
1795199772 49
1795199777 49
1795199782 49
1795199787 49
1795199792 49
1795199797 49
1795199802 49
1795199807 49
1795199812 49
1795199817 49
1795199822 49
1795199827 49
1795199832 49
1795199837 49
1795199842 49
1795199847 49
1795199852 49
```
</details>

---

