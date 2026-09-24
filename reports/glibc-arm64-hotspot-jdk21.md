---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:28:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1790241552 43
1790241557 43
1790241562 43
1790241567 43
1790241572 43
1790241577 43
1790241582 43
1790241587 43
1790241592 43
1790241597 43
1790241602 43
1790241607 42
1790241612 42
1790241617 42
1790241622 42
1790241627 42
1790241632 42
1790241637 42
1790241642 42
1790241647 42
```
</details>

---

