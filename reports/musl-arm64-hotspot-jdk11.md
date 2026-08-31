---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 11:44:51 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 13 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1788190771 22
1788190776 22
1788190781 22
1788190786 22
1788190791 22
1788190796 22
1788190801 22
1788190806 22
1788190811 22
1788190816 22
1788190821 22
1788190826 22
1788190831 22
1788190836 22
1788190841 22
1788190846 22
1788190851 20
1788190856 20
1788190861 20
1788190866 20
```
</details>

---

