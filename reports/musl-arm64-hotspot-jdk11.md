---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 07:28:17 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 12 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1790248703 48
1790248708 48
1790248713 48
1790248718 48
1790248723 48
1790248728 47
1790248733 47
1790248738 47
1790248743 47
1790248748 47
1790248753 47
1790248758 46
1790248763 46
1790248768 46
1790248773 46
1790248778 46
1790248783 46
1790248788 46
1790248793 47
1790248798 47
```
</details>

---

