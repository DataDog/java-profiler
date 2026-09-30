---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 12:30:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 19-31 cores)</summary>

```
1790785516 19
1790785521 19
1790785526 19
1790785531 19
1790785536 31
1790785541 31
1790785546 31
1790785551 31
1790785556 31
1790785561 31
1790785566 31
1790785571 31
1790785576 31
1790785581 31
1790785586 31
1790785591 31
1790785596 31
1790785601 31
1790785606 31
1790785611 31
```
</details>

---

