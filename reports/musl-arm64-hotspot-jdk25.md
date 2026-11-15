---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 08:56:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 12 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794750694 43
1794750699 43
1794750704 43
1794750709 43
1794750714 43
1794750719 43
1794750724 43
1794750729 43
1794750734 43
1794750739 43
1794750744 43
1794750749 43
1794750754 48
1794750759 48
1794750764 48
1794750769 48
1794750774 48
1794750779 48
1794750784 48
1794750789 48
```
</details>

---

