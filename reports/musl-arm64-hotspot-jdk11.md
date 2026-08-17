---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:09:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786971647 46
1786971652 46
1786971657 46
1786971662 46
1786971667 46
1786971672 46
1786971677 46
1786971682 46
1786971687 48
1786971692 48
1786971697 48
1786971702 48
1786971707 48
1786971712 48
1786971717 48
1786971722 48
1786971727 48
1786971732 48
1786971737 48
1786971742 48
```
</details>

---

