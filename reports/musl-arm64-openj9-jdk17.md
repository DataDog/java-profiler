---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 12:58:07 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795542756 24
1795542761 24
1795542766 24
1795542771 24
1795542776 24
1795542781 24
1795542786 29
1795542791 29
1795542796 29
1795542801 29
1795542806 29
1795542811 29
1795542816 29
1795542821 29
1795542826 29
1795542831 29
1795542836 29
1795542841 29
1795542846 29
1795542851 29
```
</details>

---

