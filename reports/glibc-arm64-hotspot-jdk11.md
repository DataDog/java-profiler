---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:28:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 10 |
| Allocations | 94 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790241566 50
1790241571 50
1790241576 50
1790241581 50
1790241586 50
1790241591 50
1790241596 50
1790241601 50
1790241606 50
1790241611 50
1790241616 50
1790241621 50
1790241626 50
1790241631 50
1790241636 50
1790241641 50
1790241646 50
1790241651 50
1790241656 50
1790241661 50
```
</details>

---

