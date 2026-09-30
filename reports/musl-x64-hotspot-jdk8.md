---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-30 07:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 39-50 cores)</summary>

```
1790767611 42
1790767616 50
1790767621 50
1790767626 50
1790767631 50
1790767636 50
1790767641 50
1790767646 50
1790767651 42
1790767656 42
1790767661 42
1790767666 42
1790767671 42
1790767676 42
1790767681 42
1790767686 42
1790767691 42
1790767696 42
1790767701 39
1790767706 39
```
</details>

---

