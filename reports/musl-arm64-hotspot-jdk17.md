---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 09:23:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 12 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1786540806 36
1786540812 36
1786540817 36
1786540822 36
1786540827 36
1786540832 36
1786540837 36
1786540842 36
1786540847 36
1786540852 36
1786540857 48
1786540862 48
1786540867 48
1786540872 48
1786540877 48
1786540882 48
1786540887 48
1786540892 48
1786540897 48
1786540902 48
```
</details>

---

