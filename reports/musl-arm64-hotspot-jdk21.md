---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-26 14:48:36 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787769766 32
1787769771 32
1787769776 32
1787769781 32
1787769786 32
1787769791 32
1787769796 32
1787769801 32
1787769806 32
1787769812 32
1787769817 32
1787769822 32
1787769827 32
1787769832 32
1787769837 32
1787769842 32
1787769847 32
1787769852 32
1787769857 32
1787769862 32
```
</details>

---

