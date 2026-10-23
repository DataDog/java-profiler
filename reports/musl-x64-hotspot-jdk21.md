---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 16:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 12 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 83-86 cores)</summary>

```
1792785506 86
1792785511 86
1792785516 86
1792785521 86
1792785526 86
1792785531 83
1792785536 83
1792785541 83
1792785546 83
1792785551 83
1792785556 83
1792785561 83
1792785566 83
1792785571 83
1792785576 83
1792785581 85
1792785586 85
1792785592 85
1792785597 85
1792785602 85
```
</details>

---

