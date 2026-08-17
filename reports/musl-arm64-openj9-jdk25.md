---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:10:34 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786971637 64
1786971642 64
1786971647 64
1786971652 64
1786971657 64
1786971662 64
1786971667 64
1786971672 64
1786971677 64
1786971682 64
1786971687 64
1786971692 64
1786971698 64
1786971703 64
1786971708 64
1786971713 64
1786971718 64
1786971723 64
1786971728 64
1786971733 64
```
</details>

---

