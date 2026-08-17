---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:09:13 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 42-45 cores)</summary>

```
1786971657 42
1786971662 42
1786971667 42
1786971672 42
1786971677 42
1786971682 42
1786971687 45
1786971692 45
1786971697 45
1786971702 45
1786971707 45
1786971712 45
1786971717 42
1786971722 42
1786971727 42
1786971732 42
1786971737 42
1786971742 42
1786971747 42
1786971752 42
```
</details>

---

