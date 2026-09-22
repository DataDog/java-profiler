---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:22:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 963 |
| Sample Rate | 16.05/sec |
| Health Score | 1003% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 72-96 cores)</summary>

```
1790093717 72
1790093722 72
1790093727 72
1790093732 72
1790093737 72
1790093742 72
1790093747 72
1790093752 72
1790093757 72
1790093762 96
1790093767 96
1790093772 96
1790093777 96
1790093782 96
1790093787 96
1790093792 96
1790093797 94
1790093802 94
1790093807 94
1790093813 94
```
</details>

---

