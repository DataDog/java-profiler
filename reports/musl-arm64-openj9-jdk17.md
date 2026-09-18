---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:47:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789731706 48
1789731711 48
1789731716 48
1789731721 48
1789731726 48
1789731731 48
1789731736 48
1789731741 48
1789731746 48
1789731751 46
1789731756 46
1789731761 46
1789731766 46
1789731771 46
1789731776 46
1789731781 46
1789731786 46
1789731791 46
1789731796 46
1789731801 46
```
</details>

---

