---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 00:59:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 14 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790657751 38
1790657756 38
1790657761 38
1790657766 38
1790657771 38
1790657776 38
1790657781 38
1790657786 38
1790657791 38
1790657796 38
1790657801 38
1790657806 38
1790657811 38
1790657816 38
1790657821 38
1790657826 43
1790657831 43
1790657836 43
1790657841 43
1790657846 43
```
</details>

---

